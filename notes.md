**Current Architecture (as of the repo state)**

The project is an early-stage, educational **Command & Control (C2)** framework with a clear separation of concerns. It follows a **monolithic backend with modular components** and a decoupled frontend.

### High-Level Components

1. **Backend (C++)** – Located in `/backend`
   - **Core Server**: Uses **Crow** (C++ micro web framework) for a lightweight, high-performance HTTP(S) listener. `main.cpp` sets up routes like `/health` and `/api/agent/checkin`.
   - **Database Layer**: PostgreSQL via **libpqxx**. Simple schema in `/backend/db/schema.sql` with `agents` and `tasks` tables. Basic connection and CRUD helpers (e.g., `add_or_update_agent`).
   - **Agent Management**: `AgentManager` class (placeholders for registration and listing).
   - **Tasking Engine**: `TaskManager` with placeholders for queuing tasks and retrieving results.
   - **API Endpoints**: Dedicated files in `/backend/api/` for agents, tasks, results.
   - **Build System**: CMake (`CMAKELISTS.txt`) with targets for `c2server`, `c2cli`, and platform-specific agents.
   - **Agents**: Stubs for Linux, Windows, macOS agents (C/C++). Basic check-in and task execution capability planned.

2. **Frontend (React)** – Located in `/frontend`
   - Standard Create React App structure with `axios` for API calls.
   - Basic components and `api.js` for interacting with the backend REST API.
   - Intended for a modern web dashboard (operators manage agents, issue tasks, view results).

3. **CLI** – Early/placeholder in `backend/core/cli`.

4. **Data Flow** (Basic)
   - Agents → HTTP POST check-in to server → DB update + task polling.
   - Operator (Web/CLI) → API → Task queue in DB → Agent retrieves and executes → Results stored.

5. **Security/OPSEC (Planned but Minimal)**
   - TLS listener mentioned in README.
   - JWT auth planned.
   - Hard-coded DB credentials in current code (educational stage).

**Strengths of Current Design**:
- Clean separation: Core logic, DB, API, Agents.
- Lightweight C++ backend (good for performance and evasion awareness).
- CMake for multi-platform builds.
- Educational focus with clear roadmap in README.

**Weaknesses/Limitations (Current State)**:
- Many placeholders; core functionality is skeletal.
- No authentication/authorization yet.
- No proper configuration management, logging, or error handling.
- Monolithic single-process server (Crow app).
- No containerization, CI/CD, or deployment scripts.
- Hard-coded values and incomplete implementations.
