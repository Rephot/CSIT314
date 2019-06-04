#include"reviews.h"
#include <fstream>
#include <iostream>

int total_reviews;

Review::Review(){

}

Review::Review(string rateJob, string revDesc)
{
	jobRating = rateJob;
	reviewDesc = revDesc;
}

string Review::getJobRating()
{
	return jobRating;
}

string Review::getReviewDesc()
{
	return reviewDesc;
}

void Review::setJobRating(string rate)
{
	jobRating = rate;
}

void Review::setJobReview(string rev)
{
	reviewDesc = rev;
}