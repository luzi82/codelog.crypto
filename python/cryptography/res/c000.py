# test x509

# create private key
# sign data
# verify sign

private_key_path = 'c000.private_key.pem'
public_key_path  = 'c000.public.pem'
signature_path   = 'c000.sign'

from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives.asymmetric import rsa
from cryptography.hazmat.primitives.asymmetric import padding
import os.path

# create private key
private_key = rsa.generate_private_key(
    public_exponent=65537,
    key_size=2048,
    backend=default_backend(),
)

# save private key
with open(private_key_path, "wb") as fout:
    fout.write(private_key.private_bytes(
        encoding=serialization.Encoding.PEM,
        format=serialization.PrivateFormat.TraditionalOpenSSL,
        encryption_algorithm=serialization.BestAvailableEncryption(b'OODCAXKPDO'),
    ))

# save public key
public_key = private_key.public_key()
with open(public_key_path, "wb") as fout:
    fout.write(public_key.public_bytes(
        encoding=serialization.Encoding.PEM,
        format=serialization.PublicFormat.SubjectPublicKeyInfo,
    ))

# read data
with open('data.jpg', 'rb') as fin:
    data = fin.read()

# sign data
signature = private_key.sign(
    data,
    padding.PKCS1v15(),
    hashes.SHA256(),
)

# write signature
with open(signature_path, 'wb') as fout:
    fout.write(signature)

# verify signature
public_key.verify(
    signature = signature,
    data = data,
    padding = padding.PKCS1v15(),
    algorithm = hashes.SHA256()
)
