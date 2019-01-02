function vote(id) {
  let votes = document.getElementById(id);
  let count = parseInt(votes.innerHTML);
  count++;
  votes.innerHTML = count;
}

function votedown(id) {
  let votes = document.getElementById(id);
  let count = parseInt(votes.innerHTML);
  count--;
  votes.innerHTML = count;
}
