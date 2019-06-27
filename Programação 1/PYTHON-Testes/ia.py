#python 2.7
from pybrain.tools.shortcuts import buildNetwork
from pybrain.datasets import SupervisedDataSet
from pybrain.supervised.trainers import BackpropTrainer

ds=SupervisedDataSet(2,1)

ds.addSample((0.8,0.4),(0.7))
ds.addSample((0.5,0.7),(0.5))
ds.addSample((1.0,0.8),(0.95))



nn=buildNetwork(2,4,1,bias=True)


trainer=BackpropTrainer(nn,ds)

for i in xrange(2000):
	print(trainer.train())
	
while True:
	dormiu=float(raw_input('Dormiu: \n'))
	estudou=float(raw_input('Estudou: \n'))
	previsao=nn.activate((dormiu,estudou))[0]*10.0
	print('Previsao:'+str(previsao))