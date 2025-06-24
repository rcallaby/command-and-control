import React, { useEffect, useState } from "react";
import { fetchAgents } from "../api";

function AgentList() {
  const [agents, setAgents] = useState([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);

  useEffect(() => {
    fetchAgents()
      .then((data) => {
        setAgents(data);
        setLoading(false);
      })
      .catch((e) => {
        setError("Failed to load agents");
        setLoading(false);
      });
  }, []);

  if (loading) return <p>Loading agents...</p>;
  if (error) return <p>{error}</p>;

  return (
    <table border="1" cellPadding="8" cellSpacing="0">
      <thead>
        <tr>
          <th>Agent ID</th>
          <th>Hostname</th>
          <th>Last Seen</th>
        </tr>
      </thead>
      <tbody>
        {agents.length === 0 ? (
          <tr>
            <td colSpan="3">No agents registered</td>
          </tr>
        ) : (
          agents.map((agent) => (
            <tr key={agent.agent_id}>
              <td>{agent.agent_id}</td>
              <td>{agent.hostname}</td>
              <td>{agent.last_seen}</td>
            </tr>
          ))
        )}
      </tbody>
    </table>
  );
}

export default AgentList;
