#include "feed.hpp"
#include <iostream>
#include <stdio.h>
#include <cassert>
feed::feed(const char* path){
	assert(path);
	/* open file */
	this->fptr = fopen(path,"r");
	if (!this->fptr)
		std::cerr <<  "ERROR: Unable to open file "<<path << std::endl; 
	assert(this->fptr);
}

feed::~feed(){
	fclose(this->fptr);
}
