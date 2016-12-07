select Country.Name, sum(City.Population)
from Country inner join City on City.CountryCode = Country.Code
group by Country.Code
having sum(City.Population) <= (Country.Population-sum(City.Population));
