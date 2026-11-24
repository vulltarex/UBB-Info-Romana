package service;

import domain.Friendship;
import domain.User;
import domain.Tuple;
import repository.FriendshipRepository;
import repository.UserRepository;
import util.Streams;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.function.Predicate;
import java.util.stream.Collectors;
import java.util.stream.Stream;

/** Finds connected components and the component with the longest simple path. */
public class CommunityService {
    private final UserRepository userRepo;
    private final FriendshipRepository friendshipRepo;

    /**
     * Creates a CommunityService instance.
     * @param userRepo the users repository
     * @param friendshipRepo the friendships repository
     */
    public CommunityService(UserRepository userRepo, FriendshipRepository friendshipRepo) {
        this.userRepo = userRepo;
        this.friendshipRepo = friendshipRepo;
    }

    private Map<Long, List<Long>> createGraph() {
        Map<Long, List<Long>> graph = Streams.stream(userRepo.findAll())
                .collect(HashMap::new, (vertices, user) -> vertices.put(user.getID(), Collections.emptyList()),
                        Map::putAll);
        Map<Long, List<Long>> neighbors = Streams.stream(friendshipRepo.findAll())
                .flatMap(CommunityService::directedEdges)
                .collect(Collectors.groupingBy(Tuple::getFirst,
                        Collectors.mapping(Tuple::getSecond, Collectors.toList())));
        if (!graph.keySet().containsAll(neighbors.keySet())) {
            throw new ServiceException("Exista o prietenie cu un utilizator inexistent!");
        }
        graph.replaceAll((id, empty) -> neighbors.getOrDefault(id, empty));
        return graph;
    }

    private static Stream<Tuple<Long, Long>> directedEdges(Friendship friendship) {
        return Stream.of(friendship.getID(), new Tuple<>(friendship.getSecondUserId(), friendship.getFirstUserId()));
    }

    private void visit(Long id, Long root, Map<Long, List<Long>> graph, Map<Long, Long> roots) {
        if (roots.putIfAbsent(id, root) != null) return;
        graph.get(id).stream()
                .filter(Predicate.not(roots::containsKey))
                .forEachOrdered(friendId -> visit(friendId, root, graph, roots));
    }

    private Map<Long, Long> componentRoots(Map<Long, List<Long>> graph) {
        Map<Long, Long> roots = new LinkedHashMap<>();
        graph.keySet().forEach(id -> visit(id, id, graph, roots));
        return roots;
    }

    /**
     * Counts connected components in the current network.
     * @return the number of connected components, including isolated users
     * @throws ServiceException if a friendship references a missing user
     * @throws repository.RepositoryException if persistence fails
     * @throws UnsupportedOperationException if the backend is not implemented
     */
    public int countCommunities() {
        return Math.toIntExact(componentRoots(createGraph()).values().stream().distinct().count());
    }

    /**
     * Enumerates simple paths by backtracking. Length is measured in edges.
     * The exact algorithm is intended for small laboratory networks.
     */
    private int longestPath(Long id, Map<Long, List<Long>> graph, Set<Long> path) {
        path.add(id);
        int longest = 0;
        for (Long friendId : graph.get(id)) {
            if (!path.contains(friendId)) {
                longest = Math.max(longest, 1 + longestPath(friendId, graph, path));
            }
        }
        path.remove(id);
        return longest;
    }

    /**
     * Returns the first component with the longest simple path when lengths tie.
     * @return its users, or an empty list for an empty network
     * @throws ServiceException if a friendship references a missing user
     * @throws repository.RepositoryException if persistence fails
     * @throws UnsupportedOperationException if the backend is not implemented
     */
    public List<User> mostSociableCommunity() {
        Map<Long, List<Long>> graph = createGraph();
        Map<Long, List<Long>> communities = componentRoots(graph).entrySet().stream()
                .collect(Collectors.groupingBy(Map.Entry::getValue, LinkedHashMap::new,
                        Collectors.mapping(Map.Entry::getKey, Collectors.toList())));
        return communities.values().stream()
                .map(ids -> Map.entry(ids, communityLength(ids, graph)))
                .max(Comparator.comparingInt(Map.Entry::getValue))
                .map(Map.Entry::getKey)
                .map(ids -> ids.stream().map(userRepo::findOne).collect(Collectors.toCollection(ArrayList::new)))
                .orElseGet(ArrayList::new);
    }

    private int communityLength(List<Long> ids, Map<Long, List<Long>> graph) {
        return ids.stream().mapToInt(id -> longestPath(id, graph, new HashSet<>())).max().orElse(0);
    }
}
