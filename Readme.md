graph TD;
    User -->|Google Login| GoogleAuth;
    User -->|Create/Join Team| TeamManagement;
    TeamManagement -->|Stores Data| TeamsDB;
    User -->|Select Track| TrackSelection;
    TrackSelection -->|Updates| TeamsDB;
    User -->|Submit Software Review| SoftwareReview;
    SoftwareReview -->|Stores Data| SWReviewDB;
    User -->|Submit Hardware Review| HardwareReview;
    HardwareReview -->|Stores Data| HWReviewDB;

    %% Databases
    subgraph Databases
        TeamsDB[Teams Table]
        SWReviewDB[Software Reviews Table]
        HWReviewDB[Hardware Reviews Table]
    end

graph TD;
    subgraph Google Authentication
        User -->|Google Login| GoogleAuth;
        GoogleAuth -->|Token| UserSession;
    end

    subgraph Team Management
        User -->|Create Team| CreateTeam;
        User -->|Join Team| JoinTeam;
        CreateTeam -->|Stores| TeamsDB;
        JoinTeam -->|Verifies & Updates| TeamsDB;
    end

    subgraph Review Submission
        User -->|Submit Software Review| SubmitSWReview;
        SubmitSWReview -->|Validate & Store| SWReviewDB;
        User -->|Submit Hardware Review| SubmitHWReview;
        SubmitHWReview -->|Validate & Store| HWReviewDB;
    end
#   C r y p t o _ C o d e s  
 