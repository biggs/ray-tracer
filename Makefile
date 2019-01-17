all:
	clang++ -Wall bluesky.cpp -o generate_image
display:
	./generate_image > image.ppm
	open image.ppm
clean:
	rm generate_image image.ppm
