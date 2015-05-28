var PNG = require('png-js');

//  GBRGBRGB    RGBRGBRG    BRGBRGBR
//  10001000    11000101    01100010

var width = 128;
var height = 64;

var byteArray = [];
for(var w = 0;w<width;w++){
	var column = [];
	for(var h = 0;h<height;h++)
		column[h] = 0;

	byteArray[w] = column;
}
PNG.decode('test.png', function(pixels) {
	if (pixels.length != 64*128*4)
		throw "The image must be 64 x 128 !";
	
	for(var i = 0;i < pixels.length;i++)
		console.log(pixels[i]);
});