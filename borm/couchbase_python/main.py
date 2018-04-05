from couchbase.cluster import Cluster
from couchbase.cluster import PasswordAuthenticator
from pprint import pprint
cluster = Cluster('couchbase://localhost:8091')
authenticator = PasswordAuthenticator('ignazk', 'wolfer123')
cluster.authenticate(authenticator)
cb = cluster.open_bucket("test_bucket")
pprint(cb.upsert('u:me', {'name': 'nutzlos', 'email': 'end@me.pls', 'interests': ['zuadichtn', 'goasmas'], 'website' : 'reddit.com/r/2meirl4meirl'}))
# OperationResult<RC=0x0, Key=u'u:me', CAS=0x150cbdc50aee0000>
pprint(cb.get('u:me').value)
# {'name': 'nutzlos', 'email': 'end@me.pls', 'interests': ['zuadichtn', 'goasmas'], 'website': 'reddit.com/r/2meirl4meirl'}