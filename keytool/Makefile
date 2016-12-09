# variabiles
theCountry := CN
theState := Shanghai
theLocation := Shanghai
theOrg := XXX Co., Ltd
theOrgUnit := infra
theCommonName := gerrit
theEmail := webmaster@XX.com
thePassword := somepassword
theDaysToExpire := 180
theKeyLength := 8192

# common
key_stem := 2017key
rsa_key := $(key_stem).rsa.pem
pk8_key := $(key_stem).pk8
pfx_cert := $(key_stem).pfx
csr_file := $(key_stem).csr
crt_file := $(key_stem).crt
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
.PHONY: crt clean pk8 rsa pfx

# goals
crt: rsa pk8
ifdef v3_crt
crt: $(TMP_CONFIG)
	@echo "$(TAG) Generating v3 CSR ($(csr_file)) ..."
	openssl req -new -key $(rsa_key) -out $(csr_file) -subj $(theSubj)
	@echo "$(TAG) Generating v3 cert ($(crt_file))..."
	openssl x509 -req -in $(csr_file) -extfile $(TMP_CONFIG) -extensions me_v3_ca -signkey $(rsa_key) -out $(crt_file) -days $(theDaysToExpire)
	@echo "$(TAG) Generating pkcs12 cert ($(pfx_cert))..."
	openssl pkcs12 -export -out $(pfx_cert) -inkey $(rsa_key) -in $(crt_file) -password pass:$(thePassword)
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

