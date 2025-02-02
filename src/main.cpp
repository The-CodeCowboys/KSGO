// #include "raylib.h"
// #include "networking.hpp"
#include "rtc/rtc.hpp"
#include <string>
#include <iostream>

using std::string;

int main(void) {
    rtc::Configuration config;
    config.iceServers.emplace_back("mystunserver.org:3478");

    rtc::PeerConnection pc(config);

    pc.onLocalDescription([](rtc::Description sdp) {
        // Send the SDP to the remote peer
        std::cout << "onLocalDescription: " << string(sdp) << std::endl;
    });

    pc.onLocalCandidate([](rtc::Candidate candidate) {
        // Send the candidate to the remote peer
        std::cout << "candidate.candidate(): " << string(sdp) << std::endl;
        MY_SEND_CANDIDATE_TO_REMOTE(candidate.candidate(), candidate.mid());
    });

    MY_ON_RECV_DESCRIPTION_FROM_REMOTE([&pc](string sdp) {
        pc.setRemoteDescription(rtc::Description(sdp));
    });

    MY_ON_RECV_CANDIDATE_FROM_REMOTE([&pc](string candidate, string mid) {
        pc.addRemoteCandidate(rtc::Candidate(candidate, mid));
    });

    while (true) {}

    return 0;
}
