
docs: extra.css
	doxygen

clean:
	rm -rf html extra.css

extra.css: extra.less
	lessc extra.less extra.css

rebuild: clean docs

