-- phpMyAdmin SQL Dump
-- version 2.10.0.2
-- http://www.phpmyadmin.net
-- 
-- Serveur: localhost
-- Généré le : Sam 14 Juillet 2007 à 17:24
-- Version du serveur: 5.0.37
-- Version de PHP: 5.2.2

-- 
-- Base de données: `simres`
-- 

-- --------------------------------------------------------

-- 
-- Structure de la table `demand`
-- 

CREATE TABLE IF NOT EXISTS "demand" (
  "market" varchar(7) collate latin1_general_cs NOT NULL COMMENT 'City Pair',
  "depdate" date NOT NULL COMMENT 'Departure date',
  "classpath" varchar(3) collate latin1_general_cs NOT NULL COMMENT 'Class-Path',
  "bkgdate" date NOT NULL COMMENT 'Booking Date',
  "bkgtime" time NOT NULL COMMENT 'Booking Time',
  PRIMARY KEY  ("market","depdate","classpath","bkgdate","bkgtime")
);
