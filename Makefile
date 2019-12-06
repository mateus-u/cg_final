build:
	g++ -o a *cpp -lglut -lGLU -lGL -lm

run:
	./a /home/mateus/workspace/cg_final/config

r:
	g++ -o a *cpp -lglut -lGLU -lGL -lm
	./a /home/mateus/workspace/cg_final/config
clean:
	rm a
