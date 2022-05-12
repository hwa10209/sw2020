void FindZeroCrossings( Mat& laplacian, Mat& zero_crossings )
{
	Mat* result = new Mat( laplacian.size(), CV_8U, Scalar(0) );
	zero_crossings = *result;
	int image_rows = laplacian.rows;
	int image_channels = laplacian.channels();
	int values_on_each_row = laplacian.cols * image_channels;
	float laplacian_threshold = 0.0;
	// Find Zero Crossings
	for (int row=1; row < image_rows; row++) {
		float* prev_row_pixel = laplacian.ptr<float>(row-1) +1;
		float* curr_row_pixel = laplacian.ptr<float>(row);
		uchar* output_pixel = zero_crossings.ptr<uchar>(row) +1;
		for (int column=1; column < values_on_each_row; column++)
		{
			float prev_value_on_row = *curr_row_pixel;
			curr_row_pixel++;
			float curr_value = *curr_row_pixel;
			float prev_value_on_column = *prev_row_pixel;
			float difference = 0.0;
			if (((curr_value > 0) && (prev_value_on_row < 0)) ||
				((curr_value < 0) && (prev_value_on_row > 0)))
				difference = abs(curr_value - prev_value_on_row);
			if ((((curr_value > 0) && (prev_value_on_column < 0)) ||
				 ((curr_value < 0) && (prev_value_on_column > 0))) &&
				(abs(curr_value - prev_value_on_column) > difference))
				difference = abs(curr_value - prev_value_on_column);
 			*output_pixel = (difference > laplacian_threshold) ? 255 : 0;// (int) ((100 * difference) / laplacian_threshold);
			prev_row_pixel++;
			output_pixel++;
		}
	}
}

