//
// Created by becky on 25/12/2018.
//

#ifndef TESTDATA_IMAGEHEADER_H
#define TESTDATA_IMAGEHEADER_H


class ImageHeader {
    public:
        /// magic number
        int magicNumber;
        // number of images
        int maxImages;
        // number of columns
        int imgWidth;
        // number of rows
        int imgHeight;
};


#endif //TESTDATA_IMAGEHEADER_H
