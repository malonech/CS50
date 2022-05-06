# Runner - A Run Tracker for the Runner with No Tech
#### Video Demo:  https://youtu.be/LYw5DX2j6Y0
#### Description:

#### NOTE: For some reason, the dropdown in the run history filter section will not show when screen recording. The drop down allows the user to choose a filter parameter of either duration, distance and pace. Cheers

#### I like to run and I like tracking my runs to analyze progress, however, I don't like bringing anything with me on my runs. I want to run with my shoes, my clothing and I while also being able to track my runs. Strava
#### is a popular run tracker, but that requires some form of technology for GPS tracking. The most accessible technology to track a run using Strava is to use your cellphone (iphone, Android etc...). To me, this is bulky
#### and annoying to carry, whether its in a fanny pack, in your hand, or in a pocket. Running watches offer a minimalist approach to tracking runs, however low end Garmin watches cost upwards of 200$. This is 200$ I don't
#### want to spend. My goal was to create a webpage that allows me to track my runs solely by timing my runs, and knowing the path I ran on.

#### Introducing Runner.

#### Runner is a run tracking website based on strava, but without the GPS requirement. Fundamentally, runs are tracked by tracing the run path on a map to determine distance ran, and inputting the time the run took.
#### This is accomplished by using a google maps GUI that sums the distance between markers placed on a google maps interface and by timing the run. The webpage then calculates the pace at which you ran and the calories you burned on the
#### run based on body weight and known formulas. From there, the distance, time, pace, calories and date are tabullated and archived for future reference.

#### Opening Runner prompts the user to log in. If the user has not visited runner before, they can register via the "register" button in the top right. Once logged in, the user is brought to the homepage where they are presented with their
#### 10 most recent runs (or less, if less 10 runs have been entered). A side bar features their best running pace with the corresponding distance and when the run took pace, and their longest run with the correpsonding pace and timestamp of the run.
#### All of the data shown in the tables are queried from a SQL database with data from previous runs inputted into the system. Additionally, some articles I found interesting are included as well as some popular running webpage hyperlinks for easy access.
#### In the top left, we can see the webpage features, namely "Map a Run", "New Run Entry" and "Run History".

#### "Map a Run" presents the user with a google maps GUI. Clicking on the map creates a marker. The marker can be dragged if it is not placed in the desired location. Additional clicks will present additional markers, and the program will draw a line
#### between adjacent markers and sum the distance of each line. The line represents thee run path that will be run. The distances are presnted in kilometres and miles on the right. This webpage allows the user to determine a route that will achieve the
#### run distance that they wish to run. This is to be used prior to the run.

#### "New Run Entry" presents the user with a similar layout to "Map a Run", with the inclusion of a time entry. This webpage is to be used after the run. Either, the user can again input markers on the map to achieve the run length, or they can simply input the
#### length in the bar on the right if they are aware of the distance they ran. Kilometres OR miles is sufficient, both are not required. Additioanlly, the user must input the time of the run in minutes and seconds. Submitting the run will input the run data into
#### a SQL database for that user and will redirect the user to the "Run History" webpage, with the most recent run being on top.

#### "Run History" presents the user with all of the runs they have inputted into the Runner system in descending order based on timestamp. That is, the most recent is on top, with subsequent runs detailed below it. If the desired, the user can filter the run
#### history based on run duration, distance or pace via the drop down on the left by presenting the upper and lower bounds of the filter. Submit the filter will redirect the user to the same page, but the SQL database search will be executed based on the
#### prescribed filter. The side bar with personal bests and various hyperlinks is also displayed here.

#### This is the webpage Runner. It accomplishes what I need it to accompoish to track my runs. I can now run with nothing and I love it. Thanks CS50 for allowing me to make a webpage of my own that solves an issue of mine. Cheers.