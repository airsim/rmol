SELECT market, depdate, classpath, count(*)
FROM demand 
GROUP BY market, depdate, classpath;
