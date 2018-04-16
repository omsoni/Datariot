
# coding: utf-8

# In[3]:


import pandas as pd
import numpy as np
import os
import cv2
from sklearn.utils import shuffle


# In[23]:


def load_train(path, filename, image_size):
    images = []
    imgLabels = []
    img_names = []
    metadata_file = os.path.join(path, filename)
    #'./cv-tricks.com/Tensorflow-tutorials/tutorial-2-image-classifier/data/Subset1-Simplex/simpleTrainFullPhotosSortedFullAnnotations.csv'
    df = pd.read_csv(metadata_file, header=None)
    #path = "./cv-tricks.com/Tensorflow-tutorials/tutorial-2-image-classifier/data/Subset1-Simplex/"
    print(df.head(5))
    files = df.iloc[:,0].map(str)
    labels = df.iloc[:,1].values
    print('labels',labels)
    classes = pd.unique(labels)
    print('classes', classes)
    index =0
    for fl in files:
        fl = fl.replace('\\', '/')
        file = os.path.join(path, fl)
        if (not os.path.exists(file)):
            #print('file {0} does not exist'.format(file))
            index+=1
            continue ;
        image = cv2.imread(file)
        image = cv2.resize(image, (image_size, image_size),0,0, cv2.INTER_LINEAR)
        image = image.astype(np.float32)
        image = np.multiply(image, 1.0 / 255.0)
        images.append(image)
        label = np.zeros(len(classes))
        cls = labels[index]
        label[cls] = 1
        #print('Class: {0} and labels {1}', format(cls), format(label))
        index+=1
        imgLabels.append(label)
        flbase = os.path.basename(file)
        img_names.append(flbase)
 
    images = np.array(images)
    labels = np.array(labels)
    img_names = np.array(img_names)
    #print('imgLabels:{0}'.format(imgLabels))
    return images, imgLabels, img_names


# In[2]:


class DataSet(object):

  def __init__(self, images, labels, img_names):
    self._num_examples = images.shape[0]

    self._images = images
    self._labels = labels
    self._img_names = img_names
    #self._cls = cls
    self._epochs_done = 0
    self._index_in_epoch = 0

  @property
  def images(self):
    return self._images

  @property
  def labels(self):
    return self._labels

  @property
  def img_names(self):
    return self._img_names


  @property
  def num_examples(self):
    return self._num_examples

  @property
  def epochs_done(self):
    return self._epochs_done

  def next_batch(self, batch_size):
    """Return the next `batch_size` examples from this data set."""
    start = self._index_in_epoch
    self._index_in_epoch += batch_size
    #print('Batch Size {0}'.format(batch_size))
    #print('_num_examples Size {0}'.format(self._num_examples))
    
    if self._index_in_epoch > self._num_examples:
      # After each epoch we update this
      self._epochs_done += 1
      start = 0
      self._index_in_epoch = batch_size
      assert batch_size <= self._num_examples
    end = self._index_in_epoch

    #return self._images[start:end], self._labels[start:end], self._img_names[start:end], self._cls[start:end]
    return self._images[start:end], self._labels[start:end], self._img_names[start:end]


# In[1]:


def read_train_sets(train_path, filename, image_size,validation_size):
  class DataSets(object):
    pass
  data_sets = DataSets()

  images, labels, img_names = load_train(train_path,filename, image_size)
  images, labels, img_names = shuffle(images, labels, img_names)  

  if isinstance(validation_size, float):
    validation_size = int(validation_size * images.shape[0])

  validation_images = images[:validation_size]
  validation_labels = labels[:validation_size]
  validation_img_names = img_names[:validation_size]
  #validation_cls = cls[:validation_size]

  train_images = images[validation_size:]
  train_labels = labels[validation_size:]
  #print ('train labels{0}'.format(train_labels))
  train_img_names = img_names[validation_size:]
  #train_cls = cls[validation_size:]

  data_sets.train = DataSet(train_images, train_labels, train_img_names)
  data_sets.valid = DataSet(validation_images, validation_labels, validation_img_names)

  return data_sets

