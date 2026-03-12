<div align="center">

<h1 align="center">
  <img src="https://i.imgur.com/4L6KFNr.png" width="30" />
  GinTama Firewall
</h1>

* Firewall em C puro
* Filtragem de pacotes por IP e porta
* Redirecionamento automático para vídeos
* Blocklist automática de IPs maliciosos
* Arquitetura modular com separação de responsabilidades
* Configuração persistente em arquivo

---

<h1 align="center">
  <img src="https://i.imgur.com/vSRgNpa.gif" width="30"/>
  Resumo e Demonstração:
</h1>

Sistema de firewall modular em C que permite bloquear, permitir ou redirecionar conexões para URLs customizadas (como vídeos do YouTube). Suporta download automático de listas de IPs maliciosos. Ideal para controle de acesso e redirecionamento de tráfego.

--- 

<img src="https://i.imgur.com/rymUn6p.png">

</div>

---

<h1 align="center">
  <img src="https://i.imgur.com/dwyUWDH.gif" width="30"/> Features
</h1>

* **Filtragem de Pacotes**: bloqueio ou permissão por IP e porta
* **Redirecionamento**: redireciona conexões bloqueadas para vídeos
* **Wildcards**: suporte a padrões como 192.168.*.* para ranges de IPs
* **Blocklist Automática**: download e carregamento de listas de IPs maliciosos
* **Logs**: registro completo de todas as atividades do firewall
* **Simulação**: teste o firewall sem tráfego real
* **Interface Web**: visualize regras em tempo real via browser
* **Configuração Persistente**: salva e carrega regras de arquivo
* **Arquitetura Modular**: separação clara entre core, filter, redirect e blocklist
* **Cross-Platform**: suporte para Windows, Linux e macOS
* **Clean Code**: código limpo seguindo princípios SOLID adaptados para C

---

<h1 align="center">
  <img src="https://i.imgur.com/eu3StDB.gif" width="30"/> Tech Stack
</h1>

<p align="center">
  <img src="https://go-skill-icons.vercel.app/api/icons?i=c,cmake&size=64" />
</p>

---

* C99
* CMake 3.20+
* Standard C Library
* WinINet (Windows) / libcurl (Linux)

---

<h1 align="center">
  <img src="https://i.imgur.com/PFZmPWb.gif" width="30"/> Como Executar
</h1>

**Pré-requisitos**

* GCC ou Clang
* CMake 3.20+ (opcional)
* Sistema operacional: Windows, Linux ou macOS

**Compilar**

```bash
# Windows
build.bat

# Linux/macOS
chmod +x build.sh
./build.sh
```

**Executar**

```bash
# Windows
.\GinTamaFirewall.exe

# Linux/macOS
./GinTamaFirewall
```

---

<h1 align="center">
  <img src="https://cdn-icons-png.flaticon.com/512/2103/2103633.png" width="30"/> Como Usar
</h1>

**Menu Principal**

```
1. Adicionar Regra
2. Listar Regras
3. Testar Pacote
4. Salvar Configuracao
5. Carregar Configuracao
6. Ver Logs
7. Simular Trafego
8. Iniciar Interface Web
9. Carregar Blocklist Inbound
10. Carregar Blocklist Outbound
0. Sair
```

**Exemplo de Regra de Redirecionamento**

```
Escolha: 1
IP: 192.168.1.100
Porta: 80
Acao: 2 (REDIRECIONAR)
URL de Redirecionamento: https://www.youtube.com/watch?v=dQw4w9WgXcQ
```

**Exemplo com Wildcard**

```
Escolha: 1
IP: 192.168.*.* 
Porta: 0
Acao: 1 (BLOQUEAR)
```

**Carregar Blocklist Automática**

```
Escolha: 9

[INFO] Baixando lista inbound...
[OK] Download concluido
[INFO] Carregando regras...
[OK] 1523 IPs bloqueados (inbound)
```

**Simular Tráfego**

Escolha opção 7 para gerar pacotes de teste automaticamente e ver o firewall em ação.

**Interface Web**

Escolha opção 8 e acesse http://localhost:8080 no navegador para visualizar as regras.

**Testar Pacote**

```
Escolha: 3
IP de Origem: 192.168.1.50
IP de Destino: 192.168.1.100
Porta de Origem: 54321
Porta de Destino: 80

[RESULTADO] REDIRECIONADO para https://www.youtube.com/watch?v=dQw4w9WgXcQ
[INFO] Abrindo navegador...
```

---

<h1 align="center">
  <img src="https://i.imgur.com/6nSJzZ2.gif" width="35"/> Blocklists Support
</h1>

O GinTama Firewall suporta download automático de listas de IPs maliciosos:

**Inbound Blocklist**
- URL: https://github.com/bitwire-it/ipblocklist/blob/main/inbound.txt
- Descrição: IPs maliciosos detectados em tráfego de entrada
- Uso: Opção 9 no menu

**Outbound Blocklist**
- URL: https://github.com/bitwire-it/ipblocklist/blob/main/outbound.txt
- Descrição: IPs maliciosos detectados em tráfego de saída
- Uso: Opção 10 no menu

As listas são baixadas automaticamente e carregadas como regras de bloqueio.

---

<h1 align="center">
  <img src="https://cdn-icons-png.flaticon.com/512/2103/2103633.png" width="30"/> Exemplos de Uso
</h1>

**Cenário 1: Bloquear rede interna**

```
1. Adicionar Regra
IP: 10.0.*.*
Porta: 0
Acao: 1 (BLOQUEAR)
```

**Cenário 2: Redirecionar porta 80**

```
1. Adicionar Regra
IP: 192.168.1.100
Porta: 80
Acao: 2 (REDIRECIONAR)
URL: https://www.youtube.com/watch?v=dQw4w9WgXcQ
```

**Cenário 3: Proteção com blocklist**

```
9. Carregar Blocklist Inbound
10. Carregar Blocklist Outbound
4. Salvar Configuracao
```

Agora você tem proteção contra milhares de IPs maliciosos conhecidos!

---

<h1 align="center"><img src="https://i.imgur.com/6nSJzZ2.gif" width="35"/> Referências e Documentações utilizadas</h1>

<h2 align="center">
  
**XDP Firewall**: [Link](https://github.com/gamemann/XDP-Firewall)  <img src="https://cdn-icons-png.flaticon.com/512/471/471662.png" width="40" />

</h2>

<h2 align="center">
  
**IP Blocklist**: [Link](https://github.com/bitwire-it/ipblocklist)  <img src="https://cdn-icons-png.flaticon.com/512/1828/1828843.png" width="40" />

</h2>

<h2 align="center">
  
**CMake Documentation**: [Link](https://cmake.org/documentation/)  <img src="https://go-skill-icons.vercel.app/api/icons?i=cmake&size=32" width="40" />

</h2>

<h2 align="center">
  
**C Programming**: [Link](https://en.cppreference.com/w/c)  <img src="https://go-skill-icons.vercel.app/api/icons?i=c&size=32" width="40" />

</h2>

