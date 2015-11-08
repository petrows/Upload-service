-- phpMyAdmin SQL Dump
-- version 3.4.4
-- http://www.phpmyadmin.net
--
-- Хост: localhost
-- Время создания: Ноя 08 2015 г., 08:56
-- Версия сервера: 1.0.16
-- Версия PHP: 5.6.13-pl0-gentoo

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";

--
-- База данных: `petro_upload`
--

-- --------------------------------------------------------

--
-- Структура таблицы `client_version`
--

DROP TABLE IF EXISTS `client_version`;
CREATE TABLE IF NOT EXISTS `client_version` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `ver` varchar(32) COLLATE utf8_unicode_ci NOT NULL,
  `veri` int(11) NOT NULL,
  `tms_publish` int(11) NOT NULL,
  `published` enum('Y','N') COLLATE utf8_unicode_ci NOT NULL DEFAULT 'N',
  `os_linux` enum('Y','N') COLLATE utf8_unicode_ci NOT NULL DEFAULT 'N',
  `os_win` enum('Y','N') COLLATE utf8_unicode_ci NOT NULL DEFAULT 'N',
  `os_macx` enum('Y','N') COLLATE utf8_unicode_ci NOT NULL DEFAULT 'N',
  `comment` text COLLATE utf8_unicode_ci NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `veri` (`veri`),
  UNIQUE KEY `ver` (`ver`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=4 ;

-- --------------------------------------------------------

--
-- Структура таблицы `file`
--

DROP TABLE IF EXISTS `file`;
CREATE TABLE IF NOT EXISTS `file` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `uid` int(11) NOT NULL,
  `upid` int(11) NOT NULL,
  `upn` int(11) NOT NULL,
  `dh` varchar(8) COLLATE utf8_unicode_ci NOT NULL,
  `file_name` varchar(128) COLLATE utf8_unicode_ci NOT NULL,
  `file_ext` varchar(16) COLLATE utf8_unicode_ci NOT NULL,
  `file_size` bigint(20) NOT NULL,
  `tms_add` int(11) NOT NULL,
  `tms_last` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=1722 ;

-- --------------------------------------------------------

--
-- Структура таблицы `page`
--

DROP TABLE IF EXISTS `page`;
CREATE TABLE IF NOT EXISTS `page` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(32) COLLATE utf8_unicode_ci NOT NULL,
  `title` varchar(1024) COLLATE utf8_unicode_ci NOT NULL,
  `text` longtext COLLATE utf8_unicode_ci NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=2 ;

-- --------------------------------------------------------

--
-- Структура таблицы `upload`
--

DROP TABLE IF EXISTS `upload`;
CREATE TABLE IF NOT EXISTS `upload` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `uid` int(11) NOT NULL,
  `code` varchar(32) COLLATE utf8_unicode_ci NOT NULL,
  `ph` varchar(8) COLLATE utf8_unicode_ci NOT NULL,
  `comment` varchar(512) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `tms_upload` int(11) NOT NULL,
  `tms_last` int(11) NOT NULL,
  `tms_delete` int(11) NOT NULL,
  `ttl` int(11) NOT NULL,
  `prolong` enum('Y','N') COLLATE utf8_unicode_ci NOT NULL DEFAULT 'N',
  `file_count` int(11) NOT NULL DEFAULT '0',
  `file_size` bigint(20) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  UNIQUE KEY `code` (`code`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=949 ;

-- --------------------------------------------------------

--
-- Структура таблицы `user`
--

DROP TABLE IF EXISTS `user`;
CREATE TABLE IF NOT EXISTS `user` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `pid` int(11) NOT NULL COMMENT 'Parent ID',
  `name` varchar(32) COLLATE utf8_unicode_ci NOT NULL,
  `mail` varchar(128) COLLATE utf8_unicode_ci NOT NULL,
  `passwd` varchar(32) COLLATE utf8_unicode_ci NOT NULL,
  `status` enum('ACTIVE','BANNED') COLLATE utf8_unicode_ci NOT NULL DEFAULT 'ACTIVE',
  `type` enum('REG','TMP') COLLATE utf8_unicode_ci NOT NULL DEFAULT 'REG',
  `tms_delete` int(11) NOT NULL,
  `tms_reg` int(11) NOT NULL,
  `last_login` int(11) NOT NULL,
  `last_ip` varchar(32) COLLATE utf8_unicode_ci NOT NULL,
  `login_key` varchar(32) COLLATE utf8_unicode_ci NOT NULL,
  `max_file` int(11) NOT NULL,
  `max_total` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=21 ;
