const graphviz = require("graphviz");

function generateCFD() {
  const g = graphviz.digraph("G");

  // Nodes
  g.addNode("User", { shape: "box", style: "filled", fillcolor: "#ffcc00" });
  g.addNode("GoogleAuth", {
    label: "Google Authentication",
    shape: "box",
    style: "filled",
    fillcolor: "#005f99",
    fontcolor: "white",
  });
  g.addNode("TeamMgmt", {
    label: "Team Management",
    shape: "box",
    style: "filled",
    fillcolor: "#005f99",
    fontcolor: "white",
  });
  g.addNode("SoftwareReview", {
    label: "Software Review System",
    shape: "box",
    style: "filled",
    fillcolor: "#005f99",
    fontcolor: "white",
  });
  g.addNode("HardwareReview", {
    label: "Hardware Review System",
    shape: "box",
    style: "filled",
    fillcolor: "#005f99",
    fontcolor: "white",
  });
  g.addNode("TeamsDB", {
    label: "Teams Database",
    shape: "box",
    style: "filled",
    fillcolor: "#993366",
    fontcolor: "white",
  });
  g.addNode("SoftwareDB", {
    label: "Software Reviews Database",
    shape: "box",
    style: "filled",
    fillcolor: "#993366",
    fontcolor: "white",
  });
  g.addNode("HardwareDB", {
    label: "Hardware Reviews Database",
    shape: "box",
    style: "filled",
    fillcolor: "#993366",
    fontcolor: "white",
  });

  // Edges
  g.addEdge("User", "GoogleAuth", { label: "Authenticates" });
  g.addEdge("GoogleAuth", "User", { label: "Grants Access" });
  g.addEdge("User", "TeamMgmt", { label: "Manages Team" });
  g.addEdge("TeamMgmt", "TeamsDB", { label: "Stores & Retrieves Data" });
  g.addEdge("User", "SoftwareReview", { label: "Submits Software Review" });
  g.addEdge("SoftwareReview", "SoftwareDB", { label: "Stores Data" });
  g.addEdge("User", "HardwareReview", { label: "Submits Hardware Review" });
  g.addEdge("HardwareReview", "HardwareDB", { label: "Stores Data" });

  // Render the diagram
  g.render("png", "context_flow_diagram.png");
}

generateCFD();
