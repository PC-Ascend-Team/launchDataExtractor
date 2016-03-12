disp:run
	@echo peaking at results...
	head rawData
	head ./*.txt

run:compile
	./program

compile:clean
	g++ ./*.cpp -o program

clean:
	rm -f ./*.txt program
	clear
