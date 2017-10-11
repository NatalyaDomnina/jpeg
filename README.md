### Decompression and compression jpeg image
Start the program:
```sh
app input_file.jpg
```
Changing the compression ratio (default 50):
```sh
int main (int argc, char *argv[]) {
    ...
    int factor = 50;   // compression ratio
    ...
}
```
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