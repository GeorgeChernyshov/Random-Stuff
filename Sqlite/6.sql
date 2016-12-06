select City.Name, City.Population, Country.Population
from Country inner join City on City.CountryCode = Country.Code
order by (1.0*(City.Population)/Country.Population) desc, City.Name desc limit 20;
