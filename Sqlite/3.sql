select City.Name
from City inner join Capital on City.Id = Capital.CityId
where City.CountryCode in ('MYS');
