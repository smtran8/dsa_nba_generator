# dsa_nba_generator
DSA Spring 2026 - Project 2_Group 19
Dataset: https://www.kaggle.com/datasets/sumitrodatta/nba-aba-baa-stats?select=Player+Per+Game.csv

**1. Purposes:**
   
- We want to develop a roster generator that is capable of processing thousands of historical and real-time NBA players data to identify the best 5 starting positions (roster) for NBA franchises. For each team, we would select the top 5 candidates for each position in basketball (Point Guard, Shooting Guard, Small Forward, Power Forward, Center)


**2. Methods**

- We'll solve this question based on the 2 data structures, max heap and splay tree. For max heap we would insert every player as a Node, and constantly call peek() to get the top player per position. For splay trees it would be to constantly go through the right side of the tree to get the best player per position.

**3. How to run our program**

- We built our interface using SFML in main.cpp. You'll just have to run this file to see our program. However, please note that SFML requires a Cmake file to build and run the program, therefore this is an example of how I write my CMakeLists on Window. You could use any method of CMake that you feel comfortable, but our method uses fetching content from SFML github repository. Please also pay attention to our SFML version to ensure no mismatch occurs.

**Code Example for CMake:** <br>
<img width="1194" height="655" alt="image" src="https://github.com/user-attachments/assets/84675105-2a1d-4429-8296-31bfce2bdacd" />

**4. What does the program includes**

If you have a working CMake file and successfully runs the project, this would be our interface:

<img width="1396" height="924" alt="image" src="https://github.com/user-attachments/assets/cf6cce07-4577-45e1-b093-dbd2a48c3356" />

Here you can choose whatever methods you prefer. It will have the same effects and results for both data structure, just the time complexity is different. Let's say you click on either of the data structure, you should see this program pop up:

<img width="1395" height="929" alt="image" src="https://github.com/user-attachments/assets/b5ff601e-8340-4681-984d-6dc56fd86da1" />

Now you are set to explore the best 5 roster for your team! For example let's start with Los Angeles Lakers

<img width="1399" height="925" alt="image" src="https://github.com/user-attachments/assets/b6321744-5694-4a54-9f36-915e34996341" />
<br>
This is the best 5 roster for Lakers, feel free to explore other teams as well. Note that you might not agree with our best 5, and that is okay because you might have different standards for attributes that defines a position. To change this attribute, go to classes_and_functions.cpp, look into the function compute_grade() and change the portion of whatever attribute you want.

Note:
Some players' names might have weird font writing due to special characters in their names; this is not an issue of our data processing code but rather the dataset’s issue.
