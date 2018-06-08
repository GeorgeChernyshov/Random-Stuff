select source.name, sum(sale.sale_sum)
from source
left join client on source.id = client.source_id
left join sale on client.id = sale.client_id
group by source.name;
