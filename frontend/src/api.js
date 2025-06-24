import axios from "axios";

const API_BASE = "http://localhost:8080/api";

export async function fetchAgents() {
  const res = await axios.get(`${API_BASE}/agents`); // You'll need to add this endpoint to backend
  return res.data;
}
