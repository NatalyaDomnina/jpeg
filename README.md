### Decompression and compression jpeg image
Start the program:
```sh
app-jpg input_file.jpg [compression_ratio]
```
where 
* app-jpg - path to the application
* input_file.jpg - path to the jpg file that will be decompressed and compressed
* [compression_ratio] - optional parameter which can take values from 0 to 100 (default 50).

The result of the program is the image:
```sh
Compress50%.jpg
```
where 50 is the compression ratio.

To save the decompression image, uncomment the line:
```sh
int main (int argc, char *argv[]) {
    ...
    // save_decompress_image(); // bufer -> ppm (optional)
    ...
}
```
The work of the program is verified in QtCreator.