CREATE TABLE `users` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `nickname` varchar(30) NOT NULL,
  `email` varchar(256) NOT NULL,
  `password` varchar(32) NOT NULL,
  `reg_date` datetime NOT NULL,
  `ip` varchar(15) NOT NULL,
  `user_agent` varchar(256) NOT NULL,
  `phone` varchar (11) NOT NULL,  
  PRIMARY KEY (`id`),
  UNIQUE KEY `nickname` (`nickname`),
  UNIQUE KEY `email` (`email`),
  UNIQUE KEY `phone` (`phone`)
);