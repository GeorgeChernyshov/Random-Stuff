select Country.Name, count(City.Population)
from Country inner join City on Country.Code = City.CountryCode
where City.Population >= 1000000
group by Country.Name
order by count(City.Population) desc;
