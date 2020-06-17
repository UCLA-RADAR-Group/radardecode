#run as: python3 pixvalue.py <type>
#example: python3 pixvalue.py u4

from astropy.io import fits
import numpy as np
import sys
fits_image_filename = 'Fits/f1x1.fit'
hdul = fits.open(fits_image_filename)
data = hdul[0].data

if sys.argv[1]=="u4":
    print(data[496,8])
