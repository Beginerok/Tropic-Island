CREATE TABLE `users_data` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `users_id` int(11) NOT NULL,
  `points` int not null,  
  `step` int not null,
   `last_visit` datetime not null, 
   `version` varchar(16) not null,
    PRIMARY KEY(`id`),
   FOREIGN KEY (`users_id`) REFERENCES users (id)
  );