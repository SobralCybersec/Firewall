# Clean Code & SOLID Guidelines for Java (AI Coding Rule)

Version: 1.1  
Date: 2026-03-11  
Author: Matheus

---

You are generating Java code for a production environment.

The following rules are mandatory:

- You Must Follow like this Firewall project: https://github.com/gamemann/XDP-Firewall
- You Must Follow the documentation style defined here: https://raw.githubusercontent.com/SobralCybersec/AWS-QrCodeGenerator/refs/heads/master/README.md :

``` md
<div align="center">

<h1 align="center">
  <img src="https://i.imgur.com/2mPtxE5.png" width="30" />
  AWS QR Code Generator
</h1>

* API REST para geração de QR Codes
* Backend em Java com Spring Boot
* Armazenamento automático na AWS S3
* Arquitetura Hexagonal (Ports & Adapters)
* Containerização com Docker


---

<h1 align="center">
  <img src="https://i.imgur.com/VN6wG7g.gif" width="30"/>
  Demonstração
</h1>

https://github.com/user-attachments/assets/b88caca6-da3e-4939-8084-7b61da3bf68d

---

<h1 align="center">
  <img src="https://i.imgur.com/vSRgNpa.gif" width="30"/>
  Documentação
</h1>

Sistema de geração dinâmica de QR Codes com upload automático para AWS S3. Ideal para integração em sistemas que necessitam de geração de códigos QR a partir de URLs.

</div>

---

<h1 align="center">
  <img src="https://i.imgur.com/dwyUWDH.gif" width="30"/> Features
</h1>

* **Geração de QR Codes**: criação de QR Codes a partir de URLs
* **Upload Automático**: armazenamento direto na AWS S3
* **API REST**: endpoint simples e eficiente
* **Arquitetura Hexagonal**: separação clara entre domínio e infraestrutura
* **Containerização**: suporte completo para Docker
* **Build Otimizado**: gerenciamento de dependências com Maven

---

<h1 align="center">
  <img src="https://i.imgur.com/eu3StDB.gif" width="30"/> Tech Stack
</h1>

<p align="center">
  <img src="https://go-skill-icons.vercel.app/api/icons?i=java,spring,maven,aws,docker&size=64" />
</p>

---

* Java 17
* Spring Boot 3.5.8
* Maven 3.9.6
* ZXing 3.5.0 (geração de QR Codes)
* AWS SDK 2.25.61 (integração com S3)
* Docker

---

<h1 align="center">
  <img src="https://cdn-icons-png.flaticon.com/512/1157/1157109.png" width="30"/> Architecture
</h1>

<div align="center">
  
• O projeto segue **Arquitetura Hexagonal (Ports & Adapters)**.

• Fundamentos com SOLID e Clean Code.

• Separação clara entre domínio, portas e adaptadores.
</div>

---

<h1 align="center">
  <img src="https://i.imgur.com/Jvttz1s.png" width="30"/> System Flow | Fluxo
</h1>

<div align="center">
  
```
Cliente envia URL via POST
        ↓
Service gera QR Code (ZXing)
        ↓
Adapter faz upload para S3
        ↓
Sistema retorna URL pública do QR Code
        ↓
Cliente acessa imagem na AWS S3
```
</div>

---

<h1 align="center">
  <img src="https://i.imgur.com/rNaTn43.png" width="30"/> Estrutura do Projeto
</h1>

```
qrcodegenerator/
├── adapter/         # Implementações de infraestrutura (S3)
├── controller/      # Endpoints REST
├── dto/
│   ├── request/     # DTOs de entrada
│   └── response/    # DTOs de saída
├── entity/          # Entidades de domínio
├── ports/           # Interfaces (contratos)
├── service/         # Lógica de negócio
└── utils/           # Utilitários
```

---

<h1 align="center">
  <img src="https://i.imgur.com/PFZmPWb.gif" width="30"/> Como Executar
</h1>

**Pré-requisitos**

* Java 17+
* Maven 3.9+
* Conta AWS com acesso ao S3
* Docker (opcional)

**Configuração**

```bash
# Clone o repositório
git clone <seu-repositorio>
cd qrcodegenerator

# Configure variáveis de ambiente
export AWS_ACCESS_KEY_ID=<sua-access-key>
export AWS_SECRET_ACCESS_KEY=<sua-secret-key>
export AWS_REGION=us-east-2
export AWS_BUCKET_NAME=qrcodestoragesatushi
```

**Executar Localmente**

```bash
mvn clean package
java -jar target/qrcode-0.0.1-SNAPSHOT.jar
```

**Executar com Docker**

```bash
docker build -t qrcode-generator \
  --build-arg AWS_ACCESS_KEY_ID=<sua-access-key> \
  --build-arg AWS_SECRET_ACCESS_KEY=<sua-secret-key> \
  .

docker run -p 8080:8080 qrcode-generator
```

---

<h1 align="center">
  <img src="https://cdn-icons-png.flaticon.com/512/2103/2103633.png" width="30"/> API Endpoint
</h1>

**POST /qrcode**

```json
{
  "qrcodeurl": "https://exemplo.com"
}
```

**Resposta (200 OK)**

```json
{
  "url": "https://s3.us-east-2.amazonaws.com/qrcodestoragesatushi/qrcode-1234567890.png"
}
```

---

<h1 align="center">
  <img src="https://i.imgur.com/O7HwCZt.gif" width="30"/> Roadmap
</h1>

* [x] Geração de QR Codes
* [x] Upload para AWS S3
* [x] API REST
* [x] Arquitetura Hexagonal
* [x] Containerização Docker

---

<h1 align="center"><img src="https://i.imgur.com/6nSJzZ2.gif" width="35"/> Referências e Documentações utilizadas</h1>

<h2 align="center">
  
**Spring Boot Docs**: [Link](https://docs.spring.io/spring-boot/index.html)  <img src="https://go-skill-icons.vercel.app/api/icons?i=spring&size=64" width="40" />

</h2>

<h2 align="center">
  
**AWS S3 SDK**: [Link](https://docs.aws.amazon.com/sdk-for-java/latest/developer-guide/examples-s3.html)  <img src="https://go-skill-icons.vercel.app/api/icons?i=aws&size=64" width="40" />

</h2>

<h2 align="center">
  
**ZXing Library**: [Link](https://github.com/zxing/zxing)  <img src="https://cdn-icons-png.flaticon.com/512/714/714489.png" width="40" />

</h2>

<h2 align="center">
  
**Maven**: [Link](https://maven.apache.org/guides/)  <img src="https://go-skill-icons.vercel.app/api/icons?i=maven&size=32" width="40" />

</h2>

<h2 align="center">
  
**Docker**: [Link](https://docs.docker.com/)  <img src="https://go-skill-icons.vercel.app/api/icons?i=docker&size=32" width="40" />

</h2>
```

- readable
- maintainable
- modular
- aligned with SOLID principles
- aligned with Clean Code practices
- Do not describe obvious code behavior in comments.
- Comments must only explain non-obvious decisions.

# 1. Purpose

This rule defines coding standards to ensure that generated Java code is:

- readable
- maintainable
- modular
- aligned with SOLID principles
- aligned with Clean Code practices
- Do not describe obvious code behavior in comments.
- Comments must only explain non-obvious decisions.
- You Must Follow the documentation style defined here: https://raw.githubusercontent.com/SobralCybersec/AWS-QrCodeGenerator/refs/heads/master/README.md

The goal is to avoid common patterns produced by AI that generate verbose, redundant or poorly structured code.

---

# 2. General Guidelines

The AI MUST follow these principles when generating Java code.

| # | Rule | Reason |
|---|------|-------|
| 1 | Never use emojis in comments, logs, or documentation | Keeps code professional |
| 2 | Avoid redundant comments | Only explain complex logic |
| 3 | Avoid unnecessary System.out.println | Do not pollute the console |
| 4 | Use clear and meaningful variable names | Improves readability |
| 5 | Follow SOLID principles strictly | Improves maintainability |
| 6 | Each method must have a single responsibility | Reduces complexity |
| 7 | Keep code concise and readable | Avoid verbose patterns |
| 8 | Avoid redundant loops or unnecessary logic | Improves performance |
| 9 | Prefer standard Java libraries | Avoid unnecessary custom implementations |
| 10 | Optimize code like a human developer would | AI tends to generate generic solutions |
| 11 | If the AI is uncertain about an implementation, research the correct approach before generating code | Prevents hallucinated solutions |
| 12 | Avoid typical AI documentation style | You Must Follow the documentation style defined here: https://raw.githubusercontent.com/SobralCybersec/AWS-QrCodeGenerator/refs/heads/master/README.md |

---

# 3. Control Flow Rules (C)

The AI must follow these control flow practices.

## Prefer IF statements

Use `if` for simple conditions.

## Prefer SWITCH instead of long ELSE chains

Bad example:

```c
if (strcmp(status, "A") == 0) {
    ...
} else if (strcmp(status, "B") == 0) {
    ...
} else if (strcmp(status, "C") == 0) {
    ...
}
```

Preferred:

```c
switch (status) {
    case 'A':
        ...
        break;

    case 'B':
        ...
        break;

    case 'C':
        ...
        break;
}
```

## Avoid unnecessary ELSE blocks

Preferred pattern:

```c
if (condicaoInvalida) {
    return;
}

processar();
```

This reduces nesting and improves readability.

---

# 4. Error Handling Rules (C)

Avoid excessive error handling blocks scattered across the code.

Guidelines:

1. Do not centralize all logic inside defensive checks.
2. Handle errors only when meaningful recovery exists.
3. Prefer returning error codes to higher layers.
4. Use custom error codes for domain errors.

Bad example:

```c
if (executarOperacao() != 0) {
    printf("Erro na operacao\n");
}
```

Preferred:

```c
int resultado = executarOperacao();

if (resultado != 0) {
    return ERRO_OPERACAO_INVALIDA;
}
```

Error handling should be centralized when possible.

---

# 5. SOLID-like Principles (Adapted for C)

Although C does not support classes, the architecture should still respect separation of responsibilities and modular design.

## Single Responsibility Principle

Each module should have one responsibility.

Bad:

```c
void salvarPedido() {
    // salvar pedido
}

void enviarEmail() {
    // enviar email
}
```

Good:

pedido_service.c

```c
void salvarPedido() {
    // salvar pedido
}
```

notificacao_service.c

```c
void enviarEmail() {
    // enviar email
}
```

---

## Open/Closed Principle

Modules should allow extension without modifying existing code.

Prefer function pointers and modular design.

Example:

```c
typedef struct {
    void (*salvar)(void*);
} Repository;
```

---

## Liskov Substitution Principle

Implementations using function pointers must behave consistently with the expected contract.

Example:

```c
typedef struct {
    void (*salvar)(void*);
} Repository;
```

Any implementation must respect the same behavior contract.

---

## Interface Segregation Principle

Prefer small, specialized interfaces (structs with function pointers).

Bad:

```c
typedef struct {
    void (*salvar)();
    void (*deletar)();
    void (*enviarEmail)();
} Sistema;
```

Good:

```c
typedef struct {
    void (*salvar)();
    void (*deletar)();
} Persistencia;

typedef struct {
    void (*enviarEmail)();
} Notificacao;
```

---

## Dependency Inversion Principle

Depend on abstractions instead of concrete implementations.

Bad:

```c
MysqlRepository repository;
```

Good:

```c
typedef struct {
    void (*salvar)(void*);
} PedidoRepository;

typedef struct {
    PedidoRepository* repository;
} PedidoService;
```


---

# 6. Method Design Rules

Methods must follow these constraints:

1. Maximum responsibility: one task.
2. Prefer small methods.
3. Avoid deeply nested logic.
4. Avoid duplicated logic.
5. Extract reusable methods.

---

# 7. Naming Conventions

Use clear and meaningful names.

Good examples:

```java
numero
listaPares
pedidoRepository
obterPedidosAtivos
```

Bad examples:

```java
var1
tmp
x
data2
```

---

# 8. Code Style Rules

The AI must produce code that is:

- minimal
- readable
- maintainable

Avoid:

- unnecessary comments
- redundant loops
- duplicated logic
- unnecessary complexity

---

# 9. Example

Bad example (AI-style verbose code):

```java
for (Integer numero : numeros) {
    if (numero % 2 == 0) {
    System.out.println(numero + " is even");
    } else {
    System.out.println(numero + " is odd");
    }
}
```

Preferred:

```java
public static List<Integer> obterPares(List<Integer> lista) {
    return lista.stream()
    .filter(n -> n % 2 == 0)
    .collect(Collectors.toList());
}
```

---

# 10. Final Instruction for AI

When generating Java code:

1. Follow Clean Code principles.
2. Follow SOLID principles strictly.
3. Avoid unnecessary try/catch blocks.
4. Prefer `if` and `switch` instead of complex `else` chains.
5. Write code like an experienced human developer.
6. Do not generate verbose AI-style code.