

#     Linha 1: alfabeto de entrada
#    Linha 2: alfabeto da fita
#    Linha 3: simbolo que representa um espaco em branco na fita
#    Linha 4: estado inicial
#    Linha 5, coloquem uma linha indicando o conjunto de estados de aceitacao
#    Linhas 6 em diante: transicoes, uma por linha, no formato estado atual, simbolo atual,  novo estado, novo simbolo, direcao para mover a cabeca

from xml.etree import ElementTree as ET
import csv
import sys

class Transition(object):
	def __init__(self):
		self.currentState = None
		self.currentTapeSymbol = None
		self.newState = None
		self.newTapeSymbol = None
		self.headDirection = None


class Jflap2Utfpr(object):
	def __init__(self):
		self.alphabet = set()
		self.states = set()
		self.tapeSymbols = set()
		self.initialState = None
		self.finalStates = set()
		self.transitions = set()

	def convert(self, inputFile, outputFile, blankSymbol = 'B', alphabet = None):
		if alphabet is None:
			self.alphabet = self.tapeSymbols
		else:
			self.alphabet = alphabet

		self.blankSymbol = blankSymbol
		self.tapeSymbols.add(blankSymbol)

		xmldoc = ET.parse(inputFile)
		root = xmldoc.getroot()
		tm = root.find('automaton')

		for s in tm.findall('block'):
			state = s.attrib['id']
			self.states.add(state)
			if s.find('initial') is not None:
				self.initialState = state
			if s.find('final') is not None:
				self.finalStates.add(state)

		for t in tm.findall('transition'):
			transition = Transition()
			self.transitions.add(transition)
			transition.currentState = t.find('from').text
			transition.newState = t.find('to').text
			transition.headDirection = t.find('move').text
			if t.find('read').text is not None:
				transition.currentTapeSymbol = t.find('read').text
				self.tapeSymbols.add(transition.currentTapeSymbol)
			else:
				transition.currentTapeSymbol = blankSymbol
			if t.find('write').text is not None:
				transition.newTapeSymbol = t.find('write').text
				self.tapeSymbols.add(transition.newTapeSymbol)
			else:
				transition.newTapeSymbol = blankSymbol
		
		with open(outputFile, 'wb') as csvfile:
			writer = csv.writer(csvfile, delimiter=' ')
			writer.writerow(list(self.alphabet))
			writer.writerow(list(self.tapeSymbols))
			writer.writerow([self.blankSymbol])
			writer.writerow(self.initialState)
			writer.writerow(list(self.finalStates))
			for t in self.transitions:
				writer.writerow([t.currentState, t.currentTapeSymbol, t.newState, t.newTapeSymbol, t.headDirection])



if __name__ == "__main__":
	if len(sys.argv) != 3:
		print "Parametros insuficientes. Informe o nome de arquivo de entrada e o nome do arquivo de saida"
		sys.exit(1)
	converter = Jflap2Utfpr()
	converter.convert(sys.argv[1], sys.argv[2])

