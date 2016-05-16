

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

	def __lt__(self, other):
		if self.currentState != other.currentState:
			return self.currentState < other.currentState
		if self.currentTapeSymbol != other.currentTapeSymbol:
			return self.currentTapeSymbol < other.currentTapeSymbol
		return self.newState < other.newState 


class Jflap2Utfpr(object):
	def __init__(self):
		self.state_id_to_name = {}
		self.alphabet = set()
		self.states = set()
		self.initialStates = set()
		self.finalStates = set()
		self.transitions = []
		self.blankSymbol = 'B'

	def convert(self, inputFile, outputFile, blankSymbol = 'B', alphabet = None):
		self.blankSymbol = blankSymbol
		if alphabet is not None:
			self.alphabet = alphabet

		xmldoc = ET.parse(inputFile)
		root = xmldoc.getroot()
		tm = root.find('automaton')

		for s in tm.findall('state'):
			state_id = s.attrib['id']
			state_name = s.attrib['name']
			self.state_id_to_name[state_id] = state_name
			self.states.add(state_name)
			if s.find('initial') is not None:
				self.initialStates.add(state_name)
			if s.find('final') is not None:
				self.finalStates.add(state_name)

		for t in tm.findall('transition'):
			transition = Transition()
			self.transitions.append(transition)
			transition.currentState = self.state_id_to_name[t.find('from').text]
			transition.newState = self.state_id_to_name[t.find('to').text]
			if t.find('read').text is not None:
				transition.currentTapeSymbol = t.find('read').text
				self.alphabet.add(transition.currentTapeSymbol)
			else:
				transition.currentTapeSymbol = blankSymbol
			self.transitions.sort()
		
		with open(outputFile, 'wb') as csvfile:
			writer = csv.writer(csvfile, delimiter=' ')
			writer.writerow(list(self.alphabet))
			writer.writerow(list(self.states))
			writer.writerow(list(self.initialStates))
			writer.writerow(list(self.finalStates))
			for t in self.transitions:
				writer.writerow([t.currentState, t.currentTapeSymbol, t.newState])



if __name__ == "__main__":
	if len(sys.argv) != 3:
		print "Parametros insuficientes. Informe o nome de arquivo de entrada e o nome do arquivo de saida"
		sys.exit(1)
	converter = Jflap2Utfpr()
	converter.convert(sys.argv[1], sys.argv[2], "epsilon")

