-- MySQL dump 10.13  Distrib 8.0.16, for Win64 (x86_64)
--
-- Host: localhost    Database: test
-- ------------------------------------------------------
-- Server version	8.0.16

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
 SET NAMES utf8 ;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `drum`
--

DROP TABLE IF EXISTS `drum`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
 SET character_set_client = utf8mb4 ;
CREATE TABLE `drum` (
  `id` int(11) DEFAULT NULL,
  `position` int(11) DEFAULT NULL,
  `image` varchar(8) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `drum`
--

LOCK TABLES `drum` WRITE;
/*!40000 ALTER TABLE `drum` DISABLE KEYS */;
INSERT INTO `drum` VALUES (0,0,'wild'),(0,1,'wild'),(0,2,'wild'),(0,3,'wild'),(0,4,'wild'),(0,5,'wild'),(0,6,'moto'),(0,7,'moto'),(0,8,'moto'),(0,9,'moto'),(0,10,'moto'),(0,11,'moto'),(0,12,'auto1'),(0,13,'auto1'),(0,14,'auto1'),(0,15,'auto1'),(0,16,'auto1'),(0,17,'auto1'),(0,18,'auto2'),(0,19,'auto2'),(0,20,'auto2'),(0,21,'auto2'),(0,22,'auto2'),(0,23,'auto2'),(0,24,'auto11'),(0,25,'auto11'),(0,26,'auto11'),(0,27,'auto11'),(0,28,'auto11'),(0,29,'auto11');
/*!40000 ALTER TABLE `drum` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-07-11 16:23:51
