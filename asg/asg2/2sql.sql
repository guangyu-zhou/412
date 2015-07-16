#2
SELECT  `city`,`category`,`rating`,`price`, count(*) FROM `TABLE 1` GROUP BY `city`,`category`,`rating`,`price`

#3
SELECT  `state`,`category`,`rating`,`price`, count(*) FROM `TABLE 1` GROUP BY `state`,`category`,`rating`,`price`

#4
SELECT  `category`,`rating`,`price`, count(*) FROM `TABLE 1` GROUP BY `category`,`rating`,`price`

#5
SELECT  `state`,`rating`,`price`, count(*) FROM `TABLE 1` WHERE `state`='Illinois'AND `rating`='3' AND `price`='Moderate' GROUP BY `state`,`rating`,`price`  

#6
SELECT  `city`,`category`,count(*) FROM `TABLE 1` WHERE  `city`="Chicago" AND`category`= "Food" GROUP BY  `city`,`category` 
