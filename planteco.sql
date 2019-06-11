-- phpMyAdmin SQL Dump
-- version 4.8.5
-- https://www.phpmyadmin.net/
--
-- Hôte : 127.0.0.1:3306
-- Généré le :  lun. 10 juin 2019 à 18:12
-- Version du serveur :  5.7.26
-- Version de PHP :  7.2.18

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de données :  `planteco`
--

-- --------------------------------------------------------

--
-- Structure de la table `info`
--

DROP TABLE IF EXISTS `info`;
CREATE TABLE IF NOT EXISTS `info` (
  `luminosite` int(11) NOT NULL,
  `temperature` int(11) NOT NULL,
  `humidite` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Structure de la table `plante`
--

DROP TABLE IF EXISTS `plante`;
CREATE TABLE IF NOT EXISTS `plante` (
  `nom` varchar(255) NOT NULL,
  `categorie` varchar(255) NOT NULL,
  `description` varchar(255) NOT NULL,
  `photo` varchar(255) NOT NULL,
  `minhumidite` int(11) NOT NULL,
  `mintemperature` int(11) NOT NULL,
  `luminosite` int(11) NOT NULL,
  `floraison` varchar(255) NOT NULL,
  `plante_id` int(11) NOT NULL AUTO_INCREMENT,
  `maxtemperature` int(11) NOT NULL,
  `maxhumidite` int(11) NOT NULL,
  PRIMARY KEY (`plante_id`)
) ENGINE=MyISAM AUTO_INCREMENT=4 DEFAULT CHARSET=latin1;

--
-- Déchargement des données de la table `plante`
--

INSERT INTO `plante` (`nom`, `categorie`, `description`, `photo`, `minhumidite`, `mintemperature`, `luminosite`, `floraison`, `plante_id`, `maxtemperature`, `maxhumidite`) VALUES
('Knautie des champs', 'Plante vivace', 'Plante vivace de 20-80 cm, velue, à souche épaisse et oblique.\r\nFeuilles d\'un vert terne et grisâtre, les inférieures entières, dentées ou pennatifides, à lobes lancéolés-linéaires, aigus, les moyennes ordinairement pennatiséquées.', 'https://api.tela-botanica.org/img:000226845CRS.jpg\r\n', 20, 0, 800, 'Juin Aout', 1, 30, 40),
('Picride fausse épervière', 'Plante vivace', 'Plante bisannuelle entièrement hispide, rude \r\nTige de 3-8 dm dressée, à rameaux étalés.\r\nFeuilles inférieures oblongues, entières, ondulées ou sinuées, quelquefois régulièrement pennatifides.', 'https://api.tela-botanica.org/img:001147990CRS.jpg', 5, 3, 900, 'Juillet Septembre', 2, 35, 25),
('Laurier-cerise\r\n', 'Arbuste', 'Arbuste de 3-6 mètres, toujours vert.\r\nFeuilles grandes, persistantes, très coriaces, d\'un vert sombre.', 'https://api.tela-botanica.org/img:000213057CRS.jpg', 20, -5, 900, 'Juin', 3, 32, 45);

-- --------------------------------------------------------

--
-- Structure de la table `usr`
--

DROP TABLE IF EXISTS `usr`;
CREATE TABLE IF NOT EXISTS `usr` (
  `nom` varchar(255) NOT NULL,
  `modepasse` varchar(255) NOT NULL,
  `usr_id` int(11) NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`usr_id`)
) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;

--
-- Déchargement des données de la table `usr`
--

INSERT INTO `usr` (`nom`, `modepasse`, `usr_id`) VALUES
('Utilisateur', '63a9f0ea7bb98050796b649e85481845', 1);

-- --------------------------------------------------------

--
-- Structure de la table `usrplante`
--

DROP TABLE IF EXISTS `usrplante`;
CREATE TABLE IF NOT EXISTS `usrplante` (
  `plante_id` int(11) NOT NULL,
  `usrplante_id` int(11) NOT NULL AUTO_INCREMENT,
  `usr_id` int(11) NOT NULL,
  PRIMARY KEY (`usrplante_id`),
  KEY `FK_plante` (`plante_id`),
  KEY `FK_user` (`usr_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
