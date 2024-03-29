#ifndef COMMON_HPP
#define COMMON_HPP

#include <QtWidgets>
#include <utility>
#include <set>

const uint lg1_revision = 8358;

typedef std::pair<size_t,QString> dirmap_e;
typedef std::set<dirmap_e,std::greater<dirmap_e> > dirmap_t;

QString find_newest(const dirmap_t& dirs, const QString& name);

size_t read_revision(const QString& name);

bool check_files(const dirmap_t& dirs);

QString decrypt_to_tmp(const QString& file);

#endif // COMMON_HPP
