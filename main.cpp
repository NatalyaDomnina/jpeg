#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <string>

#include <jpeglib.h>

using namespace std;

unsigned char *bmp_buffer; // image after decompression
int width, height, pixel_size, bmp_size;

void decompress (char *input_file) {
    // loading the jpeg image
    ifstream infile(input_file, ios::binary);
    if (!infile) {
        cout << "Error opening the input jpg file." << endl;
        return;
    }

    unsigned char *jpg_buffer; // input image
    int row_stride;
    vector <unsigned char> buffer_tmp;

    // initialization of decompression structures
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    // transfer of the image to the buffer
    int i = 0;
    while (infile){
        buffer_tmp.push_back(infile.get());
        i++;
    }
    infile.close();

    int jpg_size = buffer_tmp.size();
    jpg_buffer = &buffer_tmp[0];

    // create of decompression structures
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);

    // seting memory buffer as source
    jpeg_mem_src(&cinfo, jpg_buffer, jpg_size);

    // reading the JPEG header
    jpeg_read_header(&cinfo, TRUE);

    cout << "Start decompress" << endl;
    jpeg_start_decompress(&cinfo);

    // image size determination
    width = cinfo.output_width;
    height = cinfo.output_height;
    pixel_size = cinfo.output_components;

    bmp_size = width * height * pixel_size;
    bmp_buffer = new unsigned char [bmp_size];

    row_stride = width * pixel_size;

    // reading scanlines
    while (cinfo.output_scanline < cinfo.output_height) {
        unsigned char *buffer_array[1];
        buffer_array[0] = bmp_buffer + (cinfo.output_scanline) * row_stride;
        jpeg_read_scanlines(&cinfo, buffer_array, 1);
    }

    // completion of decompression
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    cout << "End of decompress" << endl;

    // freeing memory
    buffer_tmp.clear();
    buffer_tmp.shrink_to_fit();
}

void save_decompress_image() {
    ofstream outfile("Decompress.ppm", ios::out);
    if (!outfile) {
        cout << "Error opening the output ppm file." << endl;
        return;
    }

    cout << "Save decompress image" << endl;

    // definition of the file header
    string out_tmp = "P6 " + to_string(width) + " " + to_string(height) + " " + "255\n";
    const char *out = out_tmp.c_str();

    // write to header and data file
    outfile.write (out,out_tmp.size());
    outfile.write (reinterpret_cast<char*>(bmp_buffer),bmp_size);
    outfile.close();
}

void compress (int factor) {
    // output file name creation
    string fileName_tmp = "Compress" + to_string(factor) + "%"+ ".jpg";
    const char *fileName = fileName_tmp.c_str();

    // opening output file
    FILE * outfile_compr = fopen(fileName, "wb");
    if (!outfile_compr) {
        cout << "Error opening the output jpg file." << endl;
        return;
    }

    int row_stride_compr;

    // initialization of compression structures
    struct jpeg_compress_struct cinfo_compr;
    struct jpeg_error_mgr jerr_compr;
    JSAMPROW row_pointer[1];

    // create of compression structures
    cinfo_compr.err = jpeg_std_error( &jerr_compr);
    jpeg_create_compress(&cinfo_compr);

    // specify data destination
    jpeg_stdio_dest(&cinfo_compr, outfile_compr);

    // set parameters for compression
    cinfo_compr.image_width = width;
    cinfo_compr.image_height = height;
    cinfo_compr.input_components = pixel_size;
    cinfo_compr.in_color_space = JCS_RGB;
    jpeg_set_defaults(&cinfo_compr);
    cinfo_compr.dct_method = JDCT_FLOAT;
    jpeg_set_quality(&cinfo_compr, factor, TRUE);

    cout << "Start compress" << endl;
    jpeg_start_compress(&cinfo_compr, TRUE);

    row_stride_compr = width * 3;

    // reading scanlines
    while (cinfo_compr.next_scanline < cinfo_compr.image_height) {
        row_pointer[0] = & bmp_buffer[cinfo_compr.next_scanline * row_stride_compr];
        (void) jpeg_write_scanlines(&cinfo_compr, row_pointer, 1);
    }

    // completion of compression
    jpeg_finish_compress(&cinfo_compr);
    jpeg_destroy_compress(&cinfo_compr);
    cout << "End of compress" << endl;

    // close the file and free up memory
    fclose(outfile_compr);
    delete[] bmp_buffer;
}

int main (int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Error in arguments." << endl;
        cout << "Run as app-jpg input_file.jpg\"." << endl;
        return 1;
    }

    int factor = 50;            // compression ratio

    decompress (argv[1]);       // jpg -> bufer
    // save_decompress_image(); // bufer -> ppm (optional)
    compress (factor);          // bufer -> jpg

    return 0;
}
