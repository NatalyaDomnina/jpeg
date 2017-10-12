### Decompression and compression jpeg image
Start the program:
```sh
app-jpg input_file.jpg [compression_ratio]
```
where [compression_ratio] optional parameter which can take values from 0 to 100 (default 50).

To save the decompression image, uncomment the line:
```sh
int main (int argc, char *argv[]) {
    ...
    // save_decompress_image(); // bufer -> ppm (optional)
    ...
}
```
The result of the program is the image:
```sh
Compress50%.jpg
```
where 50 is the compression ratio.

The work of the program is verified in QtCreator.