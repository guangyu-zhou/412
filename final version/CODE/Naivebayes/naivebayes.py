#cs412 project
#naive bayes
# 32 attributes

import csv
import sys
import collections
class Model(object):
	def __init__(self, train_tuples, test_tuples, max_index):
		self.train_tuples = train_tuples
		self.test_tuples = test_tuples
		self.max_index = max_index
		self.labelCounts = {'0':0, '1':0} # first num is label 0, second is label 1
		self.featureName = collections.defaultdict(lambda: 0) #{index: # of possible values/ the range}
		""" a map {tuple(label, feature name/index, feature value):count}
			count is 0 by default
		"""
		self.featureCounts = collections.defaultdict(lambda: 0) 
	def TrainClassifier(self):
		
		for sample in self.train_tuples:
			self.labelCounts[sample[0]] += 1 #count 0 or 1
			for i in range(1, len(sample)):
				self.featureCounts[(sample[0], i, sample[i])] += 1 # (label, index, value)


	def GeneralClassify(self, tuples):
		confusion_matrix = {'true_pos':0, 'true_neg':0, 'false_pos':0, 'false_neg':0}
		smooth_scheme = 'ignore' # or 'addone' 'ignore'  . There's not a scheme that is perfect. All come with flaws.sometimes smoothing didn't give good results
		final_labels = []
		for sample in tuples:
			cond_pos = 1.0
			cond_neg = 1.0
			for i in range(1,len(sample)):
				#feature_temp = sample[i].split(":")[0] # index
				feature_value_temp = sample[i] #value
				if smooth_scheme == 'addone':
					# add-one smoothing is applied
					if self.featureCounts[('1', i, feature_value_temp)] == 0:
						cond_pos*= float(self.featureCounts[('1', i, feature_value_temp)]+1)/(float(self.labelCounts['1'])+float(len(self.featureName[i]))+1)
					if self.featureCounts[('0', i, feature_value_temp)] == 0:
						cond_neg*= float(self.featureCounts[('0', i, feature_value_temp)]+1)/(float(self.labelCounts['0'])+float(len(self.featureName[i]))+1)
				elif smooth_scheme == 'ignore':
					# no smoothing
					if self.featureCounts[('1', i, feature_value_temp)] == 0:
						pass
					else:
						cond_pos *= float(self.featureCounts[('1',i, feature_value_temp)])/ self.labelCounts['1']
					if self.featureCounts[('0', i, feature_value_temp)] == 0:
						pass
					else:
						cond_neg *= float(self.featureCounts[('0',i, feature_value_temp)])/ self.labelCounts['0']
						
			cond_pos *= float(self.labelCounts['1'])/len(tuples)
			cond_neg *= float(self.labelCounts['0'])/len(tuples) 

			if cond_pos >= cond_neg: # predict it as positive
				final_labels.append('1')
			else: # predict as neg
				final_labels.append('0')
		return final_labels
	def ClassifyTrain(self):
		return self.GeneralClassify(self.train_tuples)
	def Test(self): # returns a dictionary of 4 numbers
		return self.GeneralClassify(self.test_tuples)
# end of Model definition.
path_to_train_file = sys.argv[1]
path_to_test_file = sys.argv[2]
def read_as_tuples(path, tuples, test_or_train):
	with open(path, 'rb') as csvfile:
		reader = csv.reader(csvfile, delimiter=',')
		if test_or_train == 'train':
			for row in reader:
				del row[0:1] # del id 
				tuples.append(row)
		else:
			for row in reader:
				tuples.append(row)
	
train_tuples = []
test_tuples = []
read_as_tuples(path_to_train_file, train_tuples, 'train')
read_as_tuples(path_to_test_file, test_tuples, 'test')

#start building model
max_index = 32
naivebayes = Model(train_tuples, test_tuples, max_index)
naivebayes.TrainClassifier()

final_labels = naivebayes.Test()

# output eight numbers
#print train_confusion_matrix
#print test_confusion_matrix
'''print "%s %s %s %s" % (train_confusion_matrix['true_pos'], train_confusion_matrix['false_neg'], train_confusion_matrix['false_pos'], train_confusion_matrix['true_neg'])
print "%s %s %s %s" % (test_confusion_matrix['true_pos'], test_confusion_matrix['false_neg'], test_confusion_matrix['false_pos'], test_confusion_matrix['true_neg'])
'''
start = 73015
identity = []
print len(final_labels)
with open("example_entry.csv", 'rb') as csvfile:
		reader = csv.reader(csvfile, delimiter=',')
		for row in reader:
			identity.append(row)
del identity[0:1]
with open('result.csv', 'wb') as csvfile:
    writer = csv.writer(csvfile, delimiter=',')
    data = []
    for i in range(0, len(final_labels)):
    	data.append([identity[i][0], final_labels[i]])
    data.insert(0, ['RefId','IsBadBuy'])
    writer.writerows(data)    
