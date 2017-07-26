#
# 各种格式的转换
#
# PEM私钥 <— to/fro --> PKCS8私钥
# PEM私钥 + 个人信息  —> CSR —> CRT(X509证书)
# PEM私钥 + CRT + 密码 —> PKCS12证书(.PFX)
# CRT + 密码 -> JKS
# PFX + 密码 -> JKS

# variabiles
theCountry := CN
theState := Shanghai
theLocation := Shanghai
theOrg := XXX Co., Ltd
theOrgUnit := infra
theCommonName := gerrit
theEmail := webmaster@XX.com
thePassword := somepassword
thePfxName := androiddebugkey
theDaysToExpire := 180
theKeyLength := 8192

# common
key_stem := 2017key
rsa_key := $(key_stem).rsa.pem
rsa_pubkey := $(key_stem).rsa.pub
pk8_key := $(key_stem).pk8
pfx_cert := $(key_stem).pfx
csr_file := $(key_stem).csr
crt_file := $(key_stem).crt
jks_file := $(key_stem).jks
jks_file2 := $(key_stem).2.jks
TMP_CONFIG := $(shell mktemp -t .cnf -u)
theSubj := '/C=$(theCountry)/ST=$(theState)/L=$(theLocation)/O=$(theOrg)/OU=$(theOrgUnit)/CN=$(theCommonName)/emailAddress=$(theEmail)'
v3_crt := TRUE
OKGREEN := "\033[22;32m"
ENDC := "\033[0m"
TAG := "$(OKGREEN)[INFO]$(ENDC)"
ext_contents := \
"[ me_v3_ca ]\n"\
"subjectKeyIdentifier=hash\n"\
"authorityKeyIdentifier=keyid:always,issuer\n"\
"basicConstraints = CA:true\n"
.PHONY: all crt clean pk8 rsa pfx jks
all: jks jks2
# goals
.DEFAULT_GOAL := all
crt: rsa pk8
ifdef v3_crt
crt: $(TMP_CONFIG)
	@echo "$(TAG) Generating v3 CSR ($(csr_file)) ..."
	openssl req -new -key $(rsa_key) -out $(csr_file) -subj $(theSubj)
	@echo "$(TAG) Generating pub-key from priv-key ..."
	openssl rsa -in $(rsa_key) -pubout -out $(rsa_pubkey)
	@echo "$(TAG) Generating v3 cert ($(crt_file))..."
	openssl x509 -req -in $(csr_file) -extfile $(TMP_CONFIG) -extensions me_v3_ca -signkey $(rsa_key) -out $(crt_file) -days $(theDaysToExpire)
	@echo "$(TAG) Cleaning .."
	rm -f $<
else
crt:
	openssl req -new -key $(rsa_key) -out $(csr_file) -subj $(theSubj)
	@echo "$(TAG) Generating v1 cert ..."
	openssl x509 -req -in $(csr_file) -signkey $(rsa_key) -out $(crt_file) -days 180
endif

clean:
	rm -f $(csr_file) $(crt_file)
$(TMP_CONFIG):
	@echo "$(TAG) Generating v3 vert config ($@) ..."
	echo $(ext_contents) > $@
rsa:
	@echo "$(TAG) Generating RSA key ($(rsa_key)) ... "
	openssl genrsa -out $(rsa_key) $(theKeyLength)
pk8: rsa
	@echo "$(TAG) Converting to PKCS8 key ($(pk8_key)) ... "
	openssl pkcs8 -nocrypt -in $(rsa_key) -topk8 -outform DER -out $(pk8_key)
	@echo "$(TAG) Converting PKCS8 key back to pem ... "
	openssl pkcs8 -nocrypt -in $(pk8_key) -inform DER -out $(rsa_key).converted
	@echo "$(TAG) Checking integrity ..."
	diff $(rsa_key) $(rsa_key).converted
	@rm -f $(rsa_key).converted
pfx: crt
	@echo "$(TAG) Generating pkcs12 cert ($(pfx_cert))..."
	openssl pkcs12 -export -out $(pfx_cert) -inkey $(rsa_key) -in $(crt_file) -password pass:$(thePassword) -name $(thePfxName)
jks: pfx
	@echo "$(TAG) Generating JKS ($(jks_file)) from pfx ..."
	keytool -importkeystore -deststorepass $(thePassword) -destkeystore $(jks_file) -srckeystore $(pfx_cert) -srcstoretype PKCS12 -srcstorepass $(thePassword)
jks2: crt
	@echo "$(TAG) Generating JKS ($(jks_file2)) from crt ..."
	keytool -importcert -file $(crt_file) -deststorepass $(thePassword) -srcstorepass $(thePassword) -keystore $(jks_file2)

#查看keystore内容
check: |$(jks_file)
check: |$(jks_file2)
check:
	keytool -list -v -deststorepass $(thePassword) -keystore $(jks_file)
	keytool -list -v -deststorepass $(thePassword) -keystore $(jks_file2)
