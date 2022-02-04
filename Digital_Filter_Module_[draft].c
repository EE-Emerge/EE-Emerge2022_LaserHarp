// Skeleton Digital Bandpass Module for ADC data
//
// Adjust input names
// adjust filtering range

// HIGH PASS FILTERS-------------------------
	// High Pass Filter for LEFT_INPUT
      for (c = 0; c < Size; c++)
         x1[c] = LEFT_INPUT[c];

      alpha = 0.88836; //<-- 200 Hz
      y1[0] = x1[0];
      for (c = 1; c < Size; c++)
         y1[c] = alpha * y1[c-1] + alpha * (x1[c] - x1[c-1]); // y1 is LEFT_INPUT after a high pass filter

    // High Pass Filter for RIGHT_INPUT
      for (c = 0; c < Size; c++)
         x2[c] = RIGHT_INPUT[c];

      alpha = 0.88836; //<-- 200 Hz
      y2[0]=x2[0];
      for (c = 1; c < Size; c++)
         y2[c] = alpha * y2[c-1] + alpha * (x2[c] - x2[c-1]); // y2 is RIGHT_INPUT after a high pass filter

// LOW PASS FILTERS-------------------------
    // Low Pass Filter for LEFT_INPUT
          for (c = 0; c < Size; c++)
             x3[c] = alpha * y1[c]; //<--- Putting in 6.0 w/ High pass filter into low pass filter (y1)

          alpha = 0.6533742139; // <-- 3000kHz
          y3[0] = x3[0];
          for (c = 1; c < Size; c++)
             y3[c] = y3[c-1] + alpha * (x3[c] - y3[c-1]); // y3 is LEFT_INPUT w/ band pass

    // Low Pass Filter for RIGHT_INPUT
         for (c = 0; c < Size; c++)
            x4[c] = alpha * y2[c]; //<--- Putting in 6.1 with High pass filter into low pass filter (y2)

         alpha = 0.6533742139; // <-- 3000kHz
         y4[0] = x4[0];
         for (c = 1; c < Size; c++)
            y4[c] = y4[c-1] + alpha * (x4[c] - y4[c-1]); // y4 is RIGHT_INPUT w/ band pass filter

