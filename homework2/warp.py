import rawpy
import matplotlib.pylab as plt

rawImage = 'intel.raw'

raw = rawpy.imread(rawImage)
rgb = raw.postprocess()
plt.imsave('new.tiff', rgb)

image = plt.imread('new.tiff')

print(image.shape)
