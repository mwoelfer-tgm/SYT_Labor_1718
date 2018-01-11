from couchbase.cluster import Cluster
from couchbase.cluster import PasswordAuthenticator
cluster = Cluster('couchbase://localhost:8091')
authenticator = PasswordAuthenticator('ignazk', 'wolfer123')
cluster.authenticate(authenticator)
cb = cluster.open_bucket("test_bucket")
#cb.upsert('u:me', {'name': 'nutzlos', 'email': 'end@me.pls', 'interests': ['zuadichtn', 'goasmas']})
# OperationResult<RC=0x0, Key=u'u:king_arthur', CAS=0xb1da029b0000>

print(cb.get('u:me').value)
# {u'incouchbase.exceptions._TimeoutError_0x17 terests': [u'Holy Grail', u'African Swallows'], u'name': u'Arthur', u'email': u'kingarthur@couchbase.com'}?