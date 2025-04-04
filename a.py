from graphviz import Digraph

def generate_cfd():
    dot = Digraph("HackPortal System CFD", format="png")
    dot.attr(size='10', rankdir='TB', splines='polyline')
    
    # Nodes
    dot.node("User", "User", shape="box", style="filled", fillcolor="#ffcc00")
    dot.node("GoogleAuth", "Google Authentication", shape="box", style="filled", fillcolor="#005f99", fontcolor="white")
    dot.node("TeamMgmt", "Team Management", shape="box", style="filled", fillcolor="#005f99", fontcolor="white")
    dot.node("SoftwareReview", "Software Review System", shape="box", style="filled", fillcolor="#005f99", fontcolor="white")
    dot.node("HardwareReview", "Hardware Review System", shape="box", style="filled", fillcolor="#005f99", fontcolor="white")
    dot.node("TeamsDB", "Teams Database", shape="box", style="filled", fillcolor="#993366", fontcolor="white")
    dot.node("SoftwareDB", "Software Reviews Database", shape="box", style="filled", fillcolor="#993366", fontcolor="white")
    dot.node("HardwareDB", "Hardware Reviews Database", shape="box", style="filled", fillcolor="#993366", fontcolor="white")
    
    # Edges
    dot.edge("User", "GoogleAuth", label="Authenticates")
    dot.edge("GoogleAuth", "User", label="Grants Access")
    dot.edge("User", "TeamMgmt", label="Manages Team")
    dot.edge("TeamMgmt", "TeamsDB", label="Stores & Retrieves Data")
    dot.edge("User", "SoftwareReview", label="Submits Software Review")
    dot.edge("SoftwareReview", "SoftwareDB", label="Stores Data")
    dot.edge("User", "HardwareReview", label="Submits Hardware Review")
    dot.edge("HardwareReview", "HardwareDB", label="Stores Data")
    
    # Render the diagram
    dot.render("context_flow_diagram", view=True)
    
# Call the function to generate the diagram
generate_cfd()
