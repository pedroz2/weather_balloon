# weather_balloon
## Source code for TMP36's weather balloon payload.


This semester-long, 5 person project went from learning the basics of electrical wiring and soldering to launching a fully operational and to-specification atmospheric weather balloon. Our group elected to include two extra sensors, the MPU-9250 Gyroscope/Accelerometer, and the BMP-280 Barometer, in hopes of simultaneously measuring acceleration and altitude. With these two sensors, we were able to deduce wind shearing forces at different altitudes throughout Earth’s atmosphere. The intended real-world application of this was to record the expected turbulence experienced by commercial airliners, and more specifically, how to avoid it. We used Altium to design a custom PCB and then had it printed to allow for a permanent board that would house our package sensors. To facilitate the use of our sensors, we created a C++ library to use them more efficiently - it won one of the class awards.

[View Final Report](https://pedroz.dev/pdfs/final_report.pdf)
[View Poster](https://pedroz.dev/pdfs/team12_poster.pdf)

