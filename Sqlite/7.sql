select Country.Name
from Country inner join City on City.CountryCode = Country.Code
group by Country.Code
having sum(City.Population) <= 0.5*(Country.Population) and Country.Population > 0;
