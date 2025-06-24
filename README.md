# C2 Server Project - Red Team Command & Control Framework

This is an example command and control server project built to educate myself on the architecture and the systems design in order to properly build such a server tool.


## Features (v1 MVP)

- C2 Core Server (FastAPI or Go)
- Web UI (React + TailwindCSS)
- CLI Interface (Python Click or Go Cobra)
- REST API (Swagger / OpenAPI docs)
- PostgreSQL data backend
- TLS-enabled HTTP/HTTPS listener
- Windows & Linux agents (staged loader)
- Shell command execution
- File upload/download
- Agent heartbeat (sleep/jitter)
- Operator audit logs
- Multi-user login (JWT auth)
- Basic Payload Builder

---

## Roadmap

### v1
- Core server
- Basic transports (HTTP/S)
- Agents (Windows/Linux)
- Tasking & result engine

### v2
- Advanced transports (DNS tunneling, QUIC)
- Malleable C2 profiles
- Modular plugin framework
- Evasion techniques
- Advanced modules (keylogger, screenshots)

### v3
- macOS & mobile agents
- Peer-to-peer agents
- Lateral movement modules
- CI/CD automation
- Full OPSEC controls
- Multi-campaign management

---

## Tech Stack

- **C2 Core Server**: C++
- **Web UI**: React 
- **DB**: PostgreSQL
- **Agents**: C/C++, Rust (Windows/Linux/macOS)
- **CLI**: C++

---

## Educational Goals

- Demonstrate secure C2 design
- Offensive tooling with OPSEC considerations
- Multi-platform agent development
- Modern UI/UX for Red Team tools
- Scalable API-driven architecture

---

## Disclaimer

**This project is for educational use only. Do not use in unauthorized environments. Follow all local laws and regulations.**

---

