error:
	@echo "Please specify a target"

deploy: 
	./build_docs.sh
	git subtree push --prefix website/ origin gh-pages

restore:
	rm -r ./website
	git checkout -- website/
