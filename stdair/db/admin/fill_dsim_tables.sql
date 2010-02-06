--
-- Note: that file is expected to be launched from the 
--       $(top_srcdir)/db/admin sub-directory, as the CSV files are 
--       to be found in $(top_srcdir)/db/data sub-directory
--

--
-- Load the Airport and City geographical details into the MySQL table
--
load data local infile '../data/airlines.csv' ignore 
into table airlines
fields terminated by ',' enclosed by '' escaped by '\\' 
ignore 1 lines;
