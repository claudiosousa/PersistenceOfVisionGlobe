var PNG = require('png-js');

var width = 128;
var height = 64;

var result = [];
var byteArrayLength = width * height * 3 / 8;
for (var i = 0; i < byteArrayLength; i++) {
	result[i] = 0;
}
//  SR23        SR22        SR21
//  RBGRBGRG    BRBGRGBR    GBRGBRGB
var mappings = [//r, g, b
	[0, 3, 6, 9, 12, 15, 18, 21],
	[1, 4, 7, 10, 13, 16, 19, 22],
	[2, 5, 8, 11, 14, 17, 20, 23]
]

// [H-A 23 W0]    [H-A 22 W0]    ...  [H-A 0 W0] 
// [H-A 23 W/2]   [H-A 22 W/2]   ...  [H-A 0 W/2]
// [H-A 23 W1]    [H-A 22 W1]    ...  [H-A 0 W1] 
// [H-A 23 W/2+1] [H-A 22 W/2+1] ...  [H-A 0 W/2+1]

// [H-A 23 W/2-1] [H-A 22 W/2-1] ...  [H-A 0 W2/1] 
// [H-A 23 W]     [H-A 22 W]     ...  [H-A 0 W] 

var srs = height / 8 * 3;
var applyPixelColors = function (x, y, colors) {
	var hHalf = Math.floor(width / 2);
	var isBack = x >= hHalf;
	var xOffsetByte = 0, yOffsetBit = 0;
	if (x < hHalf) //1st Horizontal half of image
		xOffsetByte = x * 2 * srs;
	else
		xOffsetByte = ((x - hHalf) * 2 + 1) * srs;

	var srGroup = Math.floor(y / 8);
	var srLed = y % 8;
	yOffsetBit = srGroup;
	for (var i = 0; i < colors.length; i++) {
		if (!colors[i])
			continue;
		var ledColorByte = mappings[i][srLed];
		result[xOffsetByte + ledColorByte] |= (1 << yOffsetBit);
	}
}

PNG.decode('test.png', function (pixels) {
	if (pixels.length != height * width * 4)
		throw "The image must be " + height + " x " + width + " !";

	var pixel = 0;
	for (var i = 0; i < pixels.length; i += 4) {

		var colors = [pixels[i], pixels[i + 1], pixels[i + 2]]
		if (false)
			console.log(JSON.stringify(colors) + '\t');
		applyPixelColors(pixel % width, Math.floor(pixel / width), colors)
		pixel++;
	}
	var str = JSON.stringify(result);
	console.log('{' + str.substr(1, str.length - 2) + "}");
});